function data(interface, obj, ~)
% excentury.core.DATA: PRIVATE
%
% This function is meant to be called by an excentury.core.datatype
% object. It takes care of telling the interface to transmit the
% object's data.
%
    kind = excentury.core.type(obj);
    switch kind
        case {'C', 'I', 'N', 'R'}
            interface.data(obj)
        case 'W'
            interface.trans_num(length(obj))
            interface.trans_name(obj)
        case 'T'
            % This is not implemented completly, read
            % the comments on excentury.info when the need
            % arises to transfer a class as a tensor
            interface.data(obj, numel(obj));
        otherwise
            comm_dump = excentury.dump.dump_datatype;
            tmp = comm_dump(excentury.classname(obj, true));
            tmp(@excentury.core.data, interface, obj, '');
    end
end
