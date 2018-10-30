## ! DO NOT MANUALLY INVOKE THIS setup.py, USE CATKIN INSTEAD

from distutils.core import setup, Extension
from catkin_pkg.python_setup import generate_distutils_setup
from catkin_pkg import workspaces

# fetch values from package.xml
setup_args = generate_distutils_setup(
    packages=['RMLTypeII'],
    package_dir={'': 'src'},
)

setup(**setup_args)
