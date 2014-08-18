classdef ftextparser < handle
% excentury.dump.FTEXTPARSER: Load objects from a file
%
% This object reads data from a file. See the implementation 
% of `excentury.load_file` for an example of how to use this class.
%
    properties
        fid
        read
    end
    methods
        function self = ftextparser(fname)
            % obj = ftextparser(fname)
            % Create an object to parse a file. Use the functions
            % parse and parse_info to extract the data from the file. 
            self.fid = fopen(fname, 'r');
            self.read = containers.Map;
            self.read('C1') = '%c';
            self.read('I1') = '%d';
            self.read('N1') = '%d';
            self.read('I2') = '%d';
            self.read('I4') = '%d';
            self.read('I8') = '%ld';
            self.read('N2') = '%d';
            self.read('N4') = '%d';
            self.read('N8') = '%ld';
            self.read('R4') = '%f';
            self.read('R8') = '%f';
        end
        function val = scan(self, fmt, dim)
            % scan the next token, format may be %c, %s, %d, %ld, or %f
            val = fscanf(self.fid, fmt, dim);
            fscanf(self.fid, '%c', 1);
        end
        function info = scan_info(self)
           % read the info of a variable
           tmp_type = self.scan('%c', 1);
           switch tmp_type
               case 'S'
                   info = {'S', self.scan('%s', 1)};
               case 'T'
                   info = {'T', self.scan_info};
               case 'W'
                   info = {'W'};
               otherwise
                   info = {tmp_type, self.scan('%c', 1)};
           end
        end
        function data = scan_tensor_data(self, defs, info)
            rm_ = self.scan('%d', 1);
            ndim = self.scan('%d', 1);
            if ndim == 1
                dim = [1, self.scan('%d', ndim)];
            else
                dim = self.scan('%d', ndim)';
            end
            sub = info{2};
            switch sub{1}
                case {'I', 'N', 'R'}
                    data = self.scan(self.read(cell2mat(sub)), prod(dim));
                otherwise
                    data = cell(dim);
                    for i=1:prod(dim);
                        data{i} = self.scan_data(defs, sub);
                    end
            end
            if rm_
                data = reshape(data, fliplr(dim));
                data = permute(data, ndim:-1:1);
            else
                data = reshape(data, dim);
            end
        end
        function data = scan_data(self, defs, info)
            % scan the variable data
            switch info{1}
                case 'S'
                    comm_dump = excentury.load.load_datatype;
                    key = info{2};
                    if isKey(comm_dump, key)
                        tmp = comm_dump(key);
                        data = tmp(self, defs);
                    else
                        tmp = defs(info{2});
                        data = excentury.xc_struct(info{2}, tmp);
                        for i=1:length(tmp)
                            data.(tmp{i}{1}) = self.scan_data(defs, tmp{i}{2});
                        end
                    end
                    return
                case 'T'
                    data = self.scan_tensor_data(defs, info);
                    return
                case 'W'
                    total = self.scan('%d', 1);
                    data = self.scan('%c', total);
                otherwise
                    data = self.scan(self.read(cell2mat(info)), 1);
            end
        end
        function [nvars, defs] = scan_header(self)
            % scan the file header
            defs = containers.Map;
            ndefs = self.scan('%d', 1);
            for i = 1:ndefs
                name = self.scan('%s', 1);
                tmp = cell(0);
                while 1
                    tmp{end+1} = {self.scan('%s', 1), self.scan_info}; %#ok<AGROW>
                    next = fscanf(self.fid, '%c', 1);
                    if strcmp(next, char(10))
                       break; 
                    end
                    fseek(self.fid, -1, 0);
                end
                defs(name) = tmp;
            end
            nvars = self.scan('%d', 1);
        end
        function [var, order] = parse(self)
            % parse the information and return the variables
            var = containers.Map;
            [nvars, defs] = self.scan_header;
            order = cell(1, nvars);
            for i=1:nvars
               name = self.scan('%s', 1);
               order{i} = name;
               info = self.scan_info;
               var(name) = self.scan_data(defs, info);
            end
        end
        function [var, defs] = parse_info(self)
            % return a dictionary with the information contained
            % in the file
            var = containers.Map;
            [nvars, defs] = self.scan_header;
            for i=1:nvars
               name = self.scan('%s', 1);
               var(name) = self.scan_info;
               self.scan_data(defs, var(name));
            end
        end
    end
end
