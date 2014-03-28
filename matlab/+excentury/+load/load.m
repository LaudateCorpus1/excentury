function str_obj = load(var, info)
% excentury.load.LOAD: Load objects in a class definition
%
% This function is meant to be used along with 
% excentury.load.load_datatype. See the help info on said
% function for an example of usage.
%
    info = strrep(info, '"', '''');
    str_obj = sprintf('%s = interface.scan_data(defs, %s);', var, info);
end
