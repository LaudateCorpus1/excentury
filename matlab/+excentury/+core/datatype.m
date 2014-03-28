classdef datatype
% excentury.core.DATATYPE: Container to hold matlab objects
%
% This container holds the object along with a name and the
% interface that creates it. This class is meant to be use
% by excentury.core.communicator.
%
    properties
        obj %# matlab object
        name %# object name
        interface %# the communicator
    end
    methods
        function self = datatype(obj, name, interface)
            self.obj = obj;
            self.name = name;
            self.interface = interface;
        end
        function communicate(self)
            self.interface.trans_varname(self.name);
            excentury.core.info(self.interface, self.obj);
            excentury.core.data(self.interface, self.obj, self.name);
            self.interface.trans_close();
        end
        function append_def(self)
            excentury.core.append_cls(self.interface, self.obj);
        end
        function trans_def(self)
            self.interface.trans_name(excentury.classname(self.obj));
            excentury.core.info(self.interface, self.obj, self.name);
            self.interface.trans_close();
        end
        function tname = get_type_name(self)
            tname = excentury.classname(self.obj);
        end
    end
end
