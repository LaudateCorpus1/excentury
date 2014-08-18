"""Objects

Testing module to test excentury dumping abilities.

"""

import excentury as xc

class Point(object):
    """Test object with two properties. """
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Point(%f, %f)" % (self.x, self.y)

xc.dump_datatype(Point, 'obj', '''
    XC_DUMP(DOUBLE(obj.x), "x")
    XC_DUMP(DOUBLE(obj.y), "y")
''')
xc.load_datatype(Point, '''
    x = XC_LOAD(['R', '8'])
    y = XC_LOAD(['R', '8'])
    return Point(x, y)
''')

class Line(object):
    """Test object with two properties. """
    def __init__(self, a1, a2, b1, b2):
        self.a = Point(a1, a2)
        self.b = Point(b1, b2)

    def __repr__(self):
        return "Line(%s, %s)" % (self.a, self.b)

xc.dump_datatype(Line, 'obj', '''
    XC_DUMP(obj.a, "a")
    XC_DUMP(obj.b, "b")
''')
xc.load_datatype(Line, '''
    a = XC_LOAD(['S', 'Point'])
    b = XC_LOAD(['S', 'Point'])
    return Line(a.x, a.y, b.x, b.y)
''')
