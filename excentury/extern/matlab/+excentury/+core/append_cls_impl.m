function append_cls_impl(interface, obj, ~)
% excentury.core.APPEND_CLS_IMPL: PRIVATE
%
% This function gets passed to functions defined by the user. Its
% purpose is to call the interface's store_cls function for each of
% the objects defined in the user function.
%
    interface.store_cls(obj);
end
