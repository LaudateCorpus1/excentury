function info(interface, obj, varargin)
% excentury.core.INFO: PRIVATE
%
% This function is meant to be called by an excentury.core.datatype
% object. It takes care of telling the interface to transmit the
% object's information.
%
    if nargin == 3
        comm_dump = excentury.dump.dump_datatype;
        func = comm_dump(excentury.classname(obj, true));
        func(@excentury.core.info_impl, interface, obj, varargin{1});
        return
    end
    kind = excentury.core.type(obj);
    switch kind
        case {'C', 'I', 'N', 'R', 'S'}
            interface.info(obj)
        case 'W'
            interface.trans_type('W')
        otherwise
            % For other classes that dump tensors we need to
            % create excentury.dump.dump_tensor which will behave
            % like excentury.dump.dump_datatype and will return
            % three maps: comm_dump, dump_info and get_info.
            % This will be a way of registering classes that
            % meant to be tensors. For anything else that is
            % not registered we will let the interface handle
            % the error. Hint: you will need to get the maps
            % check if the name of the object is in there
            % and call the function. i.e:
            % functionHandle(@excentury.info, interface, obj, '');
            % otherwise call the interface.
            interface.info(obj)
    end
end
