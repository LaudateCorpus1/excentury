function info_impl(interface, obj, varname)
% excentury.core.INFO_IMPL: PRIVATE
%
% This function gets passed to functions defined by the user. Its
% purpose is to call the interface's store_cls function for each of
% the objects defined in the user function.
%
    interface.trans_name(varname);
    excentury.core.info(interface, obj);
end
