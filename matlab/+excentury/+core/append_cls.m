function append_cls(interface, obj)
% excentury.core.APPEND_CLS: PRIVATE
%
% This function is meant to be called by an excentury.core.datatype
% object. It takes care of calling the interface's store_cls function
% by using the append_cls_implementation.
%
    comm_dump = excentury.dump.dump_datatype;
    key = excentury.classname(obj, true);
    if isKey(comm_dump, key)
        func = comm_dump(key);
    else
        msg = ['No call has been made to ' ...
               'excentury.dump.dump_datatype for the class "%s"'];
        error(msg, key);
    end
    func(@excentury.core.append_cls_impl, interface, obj, '');
end
