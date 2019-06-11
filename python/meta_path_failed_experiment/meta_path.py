import os
import sys
import traceback
from importlib.abc import MetaPathFinder
from importlib.util import spec_from_file_location

class TestImporter(MetaPathFinder):
    @classmethod
    def calling_file(cls):
        stack = traceback.extract_stack()
        for f in stack[1:]: # Walk the stack from the frame above this one
            if f.filename[:8] != '<frozen ':
                return f.filename
        return None

    @classmethod
    def find_spec(cls, fullname, path=None, target=None):
        fro = cls.calling_file()
        print("Trying to import", fullname, "from file {}", fro)
        print("  details:", cls, fullname, path, target)
        print("  fro[-6:]:", fro[-6:])
        if fullname == "almostbar" and fro[-6:] == "foo.py":
            return spec_from_file_location(fullname, os.path.join(os.getcwd(), "bar.py"))

sys.meta_path.insert(0, TestImporter)

import foo
