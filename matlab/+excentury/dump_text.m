function dump_text(fname, varargin)
% excentury.DUMP_TEXT: Dump matlab objects to a file
%
% The first parameter is the name of the file to which the
% objects will be dumped to.
%
% To dump an object you need to provide it to the function
% inside a cell along with a name for that object.
%
%   excentury.dump_text('tmp.xc', {3.14, 'pi'});
%
% You may specify the type of the object by either providing
% the correct type or by providing an additional element to
% the cell. For instance, to dump a short int we can do either
% one of the following:
%
%   excentury.dump_text('tmp.xc', {int16(10), 'shortInt'});
%   excentury.dump_text('tmp.xc', {10, 'shortInt', 'short'});
%   excentury.dump_text('tmp.xc', {10, 'shortInt', 'I2'});
%
    tdump = excentury.dump.ftextdumper(fname);
    for num=1:length(varargin)
        item = varargin{num};
        if length(item) == 3
            tdump.dump(item{1}, item{2}, item{3});
        else
            tdump.dump(item{1}, item{2});
        end
    end
    tdump.close
end
