function str_obj = dump(var, name)
% excentury.dump.DUMP: Dump objects in a class definition
%
% This function is meant to be used along with 
% excentury.dump.dump_datatype. See the help info on said
% function for an example of usage.
%
    str_obj = sprintf('func(interface, %s, ''%s'');', var, name);
end
