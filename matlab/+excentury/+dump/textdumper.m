classdef textdumper < excentury.core.communicator
% excentury.dump.TEXTDUMPER: Dump objects to a string
%
% This object is derived from a communicator to transfer objects
% to a text file. See the implementation of `excentury.to_text`
% for an example of how to use this class.
%
    properties
        str
    end
    methods
        function self = textdumper()
            self = self@excentury.core.communicator();
            self.open();
        end
        function open(self)
            self.str = '';
        end
        function str_obj = close(self)
            close@excentury.core.communicator(self);
            str_obj = self.str;
        end
        function info(self, obj)
           kind = excentury.core.type(obj);
           self.str = [self.str, sprintf('%c ', kind)];
           switch kind
               case {'C', 'I', 'N', 'R'}
                   tmp = whos('obj');
                   if isa(obj, 'char')
                       self.str = [self.str, sprintf('1 ')];
                   else
                       self.str = [self.str, sprintf('%d ', tmp.bytes)];
                   end
               case 'T'
                   if iscell(obj)
                       excentury.core.info(self, obj{1});
                   else
                       excentury.core.info(self, obj(1));
                   end
               otherwise
                   self.str = [self.str, sprintf('%s ', excentury.classname(obj))];
           end
        end
        function data(self, obj, varargin)
            if nargin == 3
                if isvector(obj)
                    self.str = [self.str, sprintf('0 1 %d ', numel(obj))];
                else
                    ndim = numel(size(obj));
                    self.str = [self.str, sprintf('0 %d ', ndim)];
                    self.str = [self.str, sprintf('%d ', size(obj))];
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
                    self.str = [self.str, sprintf(tmp, obj)];
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
            self.str = [self.str, sprintf(tmp, obj)];
        end
        function trans_type(self, obj)
            self.str = [self.str, sprintf('%c ', obj)];
        end
        function trans_byte(self, obj)
            self.str = [self.str, sprintf('%d ', obj)];
        end
        function trans_num(self, num)
            self.str = [self.str, sprintf('%d ', num)];
        end
        function trans_varname(self, varname)
            self.str = [self.str, sprintf('%s ', varname)];
        end
        function trans_name(self, name)
            self.str = [self.str, sprintf('%s ', name)];
        end
        function trans_num_objects(self)
            self.str = [self.str, sprintf('%d\n', length(self.obj))];
        end
        function trans_num_classes(self)
            if ~isempty(self.cls_obj)
               self.str = [self.str, sprintf('%d\n', length(self.cls_obj))];
            else
               self.str = [self.str, sprintf('%d ', length(self.cls_obj))];
            end
        end
        function trans_close(self)
           self.str = [self.str, sprintf('\n')];
        end
    end
end
