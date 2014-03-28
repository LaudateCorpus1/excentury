function str_obj = to_text(varargin)
% excentury.TO_TEXT: Dump matlab objects to a string
%
% To dump an object you need to provide it to the function
% inside a cell along with a name for that object.
%
%   excentury.dump_text({3.14, 'pi'});
%
% You may specify the type of the object by either providing
% the correct type or by providing an additional element to
% the cell. For instance, to dump a short int we can do either
% one of the following:
%
%   excentury.to_text({int16(10), 'shortInt'});
%   excentury.to_text({10, 'shortInt', 'short'});
%   excentury.to_text({10, 'shortInt', 'I2'});
%
    tdump = excentury.dump.textdumper;
    for num=1:length(varargin)
        item = varargin{num};
        if length(item) == 3
            tdump.dump(item{1}, item{2}, item{3});
        else
            tdump.dump(item{1}, item{2});
        end
    end
    str_obj = tdump.close;
end
