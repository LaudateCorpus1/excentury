classdef xc_struct < dynamicprops
% excentury.XC_STRUCT: Replacement for matlab's struct datatype
%
% This object is designed to hold data from excentury files in case
% there is no matlab function describing how to read a variable in
% the file.
    properties (Hidden)
        name_ %# class name
        info_ %# class definition
    end
    methods
        function self = xc_struct(clsname, info)
            % xc_struct(clsname, info): Constructor
            %
            % Create a dynamic class from the information provided
            % by excentury formated files/strings.
            self.name_ = clsname;
            self.info_ = info;
            for index=1:length(info)
                key = info{index}{1};
                addprop(self, key);
                prop = findprop(self, key);
                prop.SetMethod = mksetattr(key, info{index}{2});
            end
        end
        function out = classname(self)
            % xc_struct.classname: Obtain the name of the class
            %
            % The function excentury.classname should be use in favor
            % of this method since it is general and applies to all
            % matlab objects.
            %
            out = self.name_;
        end
        function out = info(self)
            % xc_struct.info: Obtain the info of the object
            %
            % Return a cell of information object describing the
            % object.
            %
            out = self.info_;
        end
        function disp(self)
            % xc_struct.disp: Overloaded disp for xc_struct
            %
            % Displays the properties of the xc_struct object.
            %
            disp(['  xc_struct[' self.name_ '] with properties: ']);
            disp(' ');
            for index=1:length(self.info_)
                key = self.info_{index}{1};
                info = self.info_{index}{2};
                disp(['    ' key ': ' excentury.core.disp_info(info)]);
            end
            disp(' ');
        end
    end
end

function h = mksetattr(key, info)
    h = @setattr;
    function setattr(self, val)
        switch info{1}
            case 'S'
                if strcmp(excentury.classname(val), info{2})
                    self.(key) = val;
                    return
                else
                    error(['Expected ' info{2}]);
                end
            case 'W'
                if isa(val, 'char')
                    self.(key) = val;
                    return
                else
                    error('Expected a string');
                end
            case 'T'
                if excentury.cmp_info(excentury.core.get_info(val), info)
                    self.(key) = val;
                else
                   error(['Expected a tensor of:' evalc('disp(info{2})')]); 
                end
                return
            otherwise
                self.(key) = excentury.core.cast_basic(val, cell2mat(info));
        end
    end
end
