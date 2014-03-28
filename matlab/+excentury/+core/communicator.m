classdef communicator < handle
% excentury.core.COMMUNICATOR: Abstract class to transfer objects
%
% Provides the basic functions of a communicator so that derived
% classes can transfer matlab objects.
%
    properties
        obj
        cls_obj
        map
    end
    methods
        function self = communicator()
            self.obj = cell(0);
            self.cls_obj = cell(0);
            self.map = containers.Map;
            self.map('C1') = '%c';
            self.map('I1') = '%d';
            self.map('N1') = '%d';
            self.map('I2') = '%d';
            self.map('I4') = '%d';
            self.map('I8') = '%ld';
            self.map('N2') = '%d';
            self.map('N4') = '%d';
            self.map('N8') = '%ld';
            self.map('R4') = '%f';
            self.map('R8') = '%f';
        end
        function dump(self, m_obj, name, varargin)
            import excentury.core.cast_basic
            import excentury.core.get_info
            import excentury.core.disp_info
            import excentury.core.datatype
            if nargin == 4
                info = varargin{1};
                if iscell(info)
                    switch info{1}
                        case {'I', 'N', 'R'}
                            m_obj = cast_basic(m_obj, cell2mat(info));
                        otherwise
                            tmp_info = get_info(m_obj);
                            if ~excentury.core.cmp_info(tmp_info, info)
                                s1 = disp_info(info);
                                s2 = disp_info(tmp_info);
                                error('%s != %s', s1, s2);
                            end
                    end
                else
                    m_obj = cast_basic(m_obj, info);
                end
            end
            self.obj{end+1} = datatype(m_obj, name, self);
            self.store_cls(m_obj);
        end
        function store_cls(self, m_obj)
            import excentury.core.type
            import excentury.core.datatype
            if type(m_obj) == 'S'
                name = excentury.classname(m_obj);
                is_in = false;
                for num=1:length(self.cls_obj)
                    item = self.cls_obj{num};
                    if strcmp(item.get_type_name, name)
                        is_in = true;
                        break
                    end
                end
                if ~is_in
                    self.cls_obj{end+1} = datatype(m_obj, '', self);
                    new_obj = self.cls_obj{end};
                    new_obj.append_def;
                end
            end
        end
        function close(self)
            self.trans_num_classes
            for num=1:length(self.cls_obj)
                self.cls_obj{num}.trans_def
            end
            self.trans_num_objects
            for num=1:length(self.obj)
                self.obj{num}.communicate
            end
        end
    end
    methods(Abstract)
        trans_type(self, obj)
        trans_byte(self, obj)
        trans_num(self, num)
        trans_varname(self, varname)
        trans_name(self, name)
        trans_num_objects(self)
        trans_num_classes(self)
        trans_close(self)
    end
end
