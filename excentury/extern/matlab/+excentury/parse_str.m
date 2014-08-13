function [var, order] = parse_str(str, varargin)
% excentury.PARSE_STR: Load matlab objects from a string
%
% The first parameter is the string object from which the
% objects will be loaded.
%
% You may provide an optional parameter to specify that the
% file should be read in binary mode. This parameter can be
% anything. You may want to provide the string 'bin' to remind
% yourself that it is being read in binary mode.
%
% This function returns a container.Map object and a cell
% containing the keys to it in the order that they were loaded.
%
% Example:
%
%   str = excentury.to_text({3.14, 'pi'});
%   [var, order] = excentury.parse_str(str);
%   disp(var(order{1}));
%
% The above example would print the first object in the string.
%
    if nargin == 2
        error('binary mode not yet implemented');
    else
        tparser = excentury.load.textparser(str);
    end
    [var, order] = tparser.parse;
end
