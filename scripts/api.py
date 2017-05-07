#!/usr/bin/env python3
import os
import sys

from jinja2 import Template
import CppHeaderParser


def walkdir(path):
    files = []
    for (dirpath, dirnames, filenames) in os.walk(path):
        for filename in filenames:
            if filename.endswith('.hpp'):
                files.append(os.sep.join([dirpath, filename]))
    files.reverse()
    return files


def clean_name(name):
    name = name.replace(" ( ", "(")
    name = name.replace(" ) ", ")")
    name = name.replace(" , ", ", ")
    name = name.replace(" & ", " &")
    name = name.replace("{", "")
    name = name.replace(";", "")

    return name


def clean_doc(element):
    # check if doxygen key exists
    if "doxygen" not in element:
        return None

    # setup
    doc = element["doxygen"]
    doc = doc.lstrip(" ")

    result = ""
    for line in doc.split("\n"):
        line = line.lstrip("/**")
        line = line.lstrip("* ")
        if len(line) > 0:
            result += line.lstrip(" ") + "\n"

    return result


# def function_docstr(fn):
#     fn_name = fn[0]
#     fn_args = pydoc.inspect.formatargspec(*pydoc.inspect.getargspec(fn[1]))
#     fn_doc = clean_docstr(fn[1].__doc__)
#
#     return {"type": "function",
#             "name": fn_name,
#             "args": fn_args,
#             "docstr": fn_doc}


# def method_docstr(mh):
#     mh_name = mh[0]
#     mh_args = pydoc.inspect.formatargspec(*pydoc.inspect.getargspec(mh[1]))
#     mh_doc = clean_docstr(mh[1].__doc__)
#
#     return {"type": "method",
#             "name": mh_name,
#             "args": mh_args,
#             "docstr": mh_doc}
#

def class_doc(cl):
    # public_methods = []
    # private_methods = []

    for mh in cl['methods']['public']:  # iterate over public functions
        mh_name = clean_name(mh["debug"])
        mh_doc = clean_doc(mh)
        print(mh_name)
        print(mh_doc)

    # return {"type": "class",
    #         "name": cl_name,
    #         # "doc": cl_doc,
    #         "public_methods": public_methods,
    #         "private_methods": private_methods}


# def docstr(file_path):
#     classes = []
#     functions = []
#
#     # setup
#     module_name = file_path.replace(".py", "").replace("/", ".")
#     print("-> {}".format(module_name))
#
#     # load module
#     module = pydoc.safeimport(module_name)
#     if module is None:
#         raise RuntimeError("Module {} not found!".format(module_name))
#     module_doc = clean_docstr(module.__doc__)
#
#     # inspect classes
#     for cl in pydoc.inspect.getmembers(module, pydoc.inspect.isclass):
#         if cl[1].__module__ == module_name:
#             classes.append(class_docstr(cl))
#
#     # inspect functions
#     for fn in pydoc.inspect.getmembers(module, pydoc.inspect.isfunction):
#         if fn[1].__module__ == module_name:
#             functions.append(function_docstr(fn))
#
#     return ({"name": module_name, "docstr": module_doc}, classes, functions)
#
#
# def genapi(module, classes, functions, output_dir="./"):
#     # setup
#     api_filename = module["name"].replace(".", "_") + ".md"
#     api_doc = open(os.path.join(output_dir, api_filename), "w")
#
#     # render api doc
#     api_template = Template("""\
# # {{module.name}}
# {% if module.docstr %}{{module.docstr}}{% endif %}\
#
# {% if classes|length > 0 %}\
# ## Classes
#
# {% for cl in classes %}\
# - {{cl.name}}
# {% endfor %}
#
# {% for cl in classes %}\
# ### {{cl.name}}
# {% if cl.docstr %}{{cl.docstr}}\n---{% endif %}
# {% for method in cl.methods %}
#     {{method.name}}{{method.args}}
#
# {% if method.docstr %}{{method.docstr}}{% endif %}
# ---
# {% endfor %}\
# {% endfor %}\
# {% endif %}\
#
# {% if functions|length > 1 %}
# ## Functions
#
# {% for fn in functions %}\
# - {{fn.name}}
# {% endfor %}
# ---
#
# {% for fn in functions %}
#     {{fn.name}}{{fn.args}}
#
# {% if fn.docstr %}{{fn.docstr}}{% endif %}
# ---
# {% endfor %}\
# {% endif %}\
# """)
#     api = api_template.render(module=module,
#                               classes=classes,
#                               functions=functions)
#
#     # output api to file
#     api_doc.write(api)
#     api_doc.close()


if __name__ == "__main__":
    files = walkdir(sys.argv[1])

    header = CppHeaderParser.CppHeader("./include/yarl/estimation/kf.hpp")

    for cl_name in header.classes:  # iterate over classes
        cl = header.classes[cl_name]

        for fn in cl['methods']['public']:  # iterate over public functions
            fn_name = clean_name(fn["debug"])
            fn_docstr = clean_doc(fn)
            print(fn_name)
            print(fn_docstr)

    # import pprint
    # pprint.pprint(header.classes)

    # for f in files:
    #     module, classes, functions = docstr(f)
    #     genapi(module, classes, functions, sys.argv[2])
