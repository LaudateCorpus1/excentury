function map = dump_datatype(varargin)
% excentury.dump.DUMP_DATATYPE: Create dumping definition
%
% If no parameters are provided then this function returns
% a dictionary containing the functions already created.
%
% To create a function you must provide 3 arguments:
%
%    excentury.dump.dump_datatype('Point', 'p', { ...
%        excentury.dump.dump('p.x', 'x'), ...
%        excentury.dump.dump('p.y', 'y') ...
%    });
%
% The above example declares the definition for dumping an object
% with classname 'Point'. To dump it, we declare a variable name
% which is assumed to be of type `Point`. In this case we called it
% `p`.
%
% Now we have a referece to the point we we must dump its attributes.
% Note that you must provide a cell of strings in the third argument.
% The function excentury.dump.dump simple does some string replacement
% and returns a string. You are allowed to put matlab commands in this
% definition as strings.
%
    persistent comm_dump;
    if isempty(comm_dump)
        comm_dump = containers.Map;
        comm_dump('xc_struct') = @dump_xc_struct;
    end
    if nargin == 0
        map = comm_dump;
        return
    end
    obj = varargin{1};
    if isKey(comm_dump, obj)
        map = comm_dump;
        return
    end
    var = varargin{2};
    content = strrep([varargin{3}{:}], var, 'var');
    comm_dump(obj) = @dump_func;
    function dump_func(func, interface, var, varname) %#ok<INUSD>
        eval(content);
    end
    map = comm_dump;
end

function dump_xc_struct(func, interface, obj, ~)
    obj_info = obj.info;
    for i=1:length(obj.info)
        info = obj_info{i};
        func(interface, obj.(info{1}), info{1});
    end
end
