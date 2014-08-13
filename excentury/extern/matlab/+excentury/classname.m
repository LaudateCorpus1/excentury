function name = classname(obj, varargin)
% excentury.CLASSNAME: Obtain the name of the class
%
% When using the class function you obtain the complete name of
% the class, i.e pkgname.classname. This function discards the
% the package name and returns only the intended name for the class.
%
    name = strsplit(class(obj), '.');
    name = name{end};
    if ~isempty(varargin)
        return
    elseif strcmp(name, 'xc_struct')
       name = obj.classname; 
    end
end
