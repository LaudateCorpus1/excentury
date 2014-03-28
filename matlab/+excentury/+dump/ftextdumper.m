classdef ftextdumper < excentury.core.communicator
% excentury.dump.FTEXTDUMPER: Dump objects to a text file
%
% This object is derived from a communicator to transfer objects
% to a text file. See the implementation of `excentury.dump_text`
% for an example of how to use this class.
%
    properties
        fname
        fid
    end
    methods
        function self = ftextdumper(fname)
            self = self@excentury.core.communicator();
            self.fid = false;
            self.open(fname);
        end
        function open(self, fname)
            self.fname = fname;
            self.fid = fopen(fname, 'w');
        end
        function close(self)
            if self.fid
               close@excentury.core.communicator(self);
               fclose(self.fid);
               self.fid = false;
            end
        end
        function info(self, obj)
           kind = excentury.core.type(obj);
           fprintf(self.fid, '%c ', kind);
           switch kind
               case {'C', 'I', 'N', 'R'}
                   tmp = whos('obj');
                   if isa(obj, 'char')
                       fprintf(self.fid, '1 ');
                   else
                       fprintf(self.fid, '%d ', tmp.bytes);
                   end
               case 'T'
                   if iscell(obj)
                       excentury.core.info(self, obj{1});
                   else
                       excentury.core.info(self, obj(1));
                   end
               otherwise
                   fprintf(self.fid, '%s ', excentury.classname(obj));
           end
        end
        function data(self, obj, varargin)
            if nargin == 3
                if isvector(obj)
                    fprintf(self.fid, '0 1 %d ', numel(obj));
                else
                    fprintf(self.fid, '0 %d ', length(size(obj)));
                    fprintf(self.fid, '%d ', size(obj));
                end
                total = varargin{1};
                if iscell(obj)
                    for i=1:total
                        excentury.core.data(self, obj{i}, '');
                    end
                else
                    kind = excentury.core.type(obj(1));
                    tmp = whos('obj');
                    if isa(obj, 'char')
                        kind = [kind '1'];
                    else
                        kind = [kind sprintf('%d', tmp.bytes/total)];
                    end
                    tmp = sprintf('%s ', self.map(kind));
                    fprintf(self.fid, tmp, obj);
                end
                return
            end
            kind = excentury.core.type(obj);
            tmp = whos('obj');
            if isa(obj, 'char')
                kind = [kind '1'];
            else
                kind = [kind sprintf('%d', tmp.bytes)];
            end
            tmp = sprintf('%s ', self.map(kind));
            fprintf(self.fid, tmp, obj);
        end
        function trans_type(self, obj)
            fprintf(self.fid, '%c ', obj);
        end
        function trans_byte(self, obj)
            fprintf(self.fid, '%d ', obj);
        end
        function trans_num(self, num)
            fprintf(self.fid, '%d ', num);
        end
        function trans_varname(self, varname)
            fprintf(self.fid, '%s ', varname);
        end
        function trans_name(self, name)
            fprintf(self.fid, '%s ', name);
        end
        function trans_num_objects(self)
            fprintf(self.fid, '%d\n', length(self.obj));
        end
        function trans_num_classes(self)
            if ~isempty(self.cls_obj)
               fprintf(self.fid, '%d\n', length(self.cls_obj)); 
            else
               fprintf(self.fid, '%d ', length(self.cls_obj)); 
            end
        end
        function trans_close(self)
           fprintf(self.fid, '\n'); 
        end
    end
end
