#!/usr/bin/env python
""" Setup script for the nuChic neutrino event generator. """

# from setuptools import setup, find_packages, Extension
from os import path
from io import open
import setuptools
from numpy.distutils.core import setup, Extension
# io.open is needed for projects that support Python 2.7
# It ensures open() defaults to text mode with universal newlines,
# and accepts an argument to specify the text encoding

EXT1 = Extension(name='xsec', sources=['nuChic/xsec.pyf',
                                       'nuChic/currents_opt_v1.f90',
                                       'nuChic/xsec.f90',
                                       'nuChic/mathtool.f90',
                                       'nuChic/nform.f90'])

HERE = path.abspath(path.dirname(__file__))

# Get the long description from the README file
with open(path.join(HERE, 'README.md'), encoding='utf-8') as f:
    LONG_DESCRIPTION = f.read()

setup(
    name='nuChic',
    version='1.0',
    description='Neutrino Event Generator',
    long_description=LONG_DESCRIPTION,
    long_description_content_type='text/markdown',
    url='https://github.com/jxi24/FNALNeuGen',
    author='Joshua Isaacson, \
            William Jay, \
            Alessandro Lovato, \
            Pedro A. Machado, \
            Stefan Prestel, \
            Noemi Rocco, \
            Holger Schulz',
    classifiers=[
        # How mature is this project? Common values are
        #   3 - Alpha
        #   4 - Beta
        #   5 - Production/Stable
        'Development Status :: 3 - Alpha',

        # Specify the Python versions you support here. In particular, ensure
        # that you indicate whether you support Python 2, Python 3 or both.
        'Programming Language :: Python :: 3',
    ],
    packages=setuptools.find_packages(),
    python_requires='>=3.5, <4',
    install_requires=[
        'numpy',
        'vegas',
        'h5py',
        'scipy',
        'pandas',
        'sklearn',
        'absl-py',
        'matplotlib',
    ],
    # Provide executable script to run the main code
    entry_points={'console_scripts': ['nuChic = nuChic.main:nu_chic', ], },
    ext_modules=[EXT1],
    package_data={'': ['data/*', 'pke/*', 'configurations/*']},
    extras_require={
        'test': ['pytest', 'coverage', 'pytest-cov'],
    },
)
