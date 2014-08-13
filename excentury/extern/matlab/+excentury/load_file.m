function [var, order] = load_file(fname, varargin)
% excentury.LOAD_FILE: Load matlab objects from a file
%
% The first parameter is the name of the file from which the
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
%   [var, order] = excentury.load_file('tmp.xc');
%   disp(var(order{1}));
%
% The above example would print the first object in the file.
%
    if nargin == 2
        error('binary mode not yet implemented');
    else
        tparser = excentury.load.ftextparser(fname);
    end
    [var, order] = tparser.parse;
end
