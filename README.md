# inizer - CLI Tool for .ini-style config files

## Overview

inizer (pronounced "/'a͡ɪː.ɛn.a͡ɪˑ.zɚ/" in standard American English, or really however you prefer) is a simple tool for querying and modifying .ini-styled configuration files. It is written in C and aims to be portable to all environments supporting GLib.

## Usage

inizer currently offers a simple command-line interface for reading and writing configuration values. It can be used directly without too much difficulty, but it is designed with use as a scripting API in mind (e.g., to be wrapped for handling app- or domain-specific configurations in shell scripts).

```shell
    ionizer get FILE_PATH SECTION_NAME KEY_NAME 
    ionizer set FILE_PATH SECTION_NAME KEY_NAME VALUE
```

where `FILE_PATH` is the absolute or relative path to the .ini file to be read or updated, `SECTION_NAME` is the configuration section under which the target setting lives, `KEY_NAME` is the name of the target setting key, and `VALUE` is the exact text representation of the value to be written when using the `set` command. inizer does no type checking or validation of values passed or retrieved; all values are written and printed as strings, retaining as high fidelity as possible for both read and write operations.

## Configuration

inizer currently does not offer any runtime configuration through its own config file or through command-line options.

## Roadmap

Features planned for inizer include:

* Shell completion functions
* man page
* More thorough help message
* `inizer unset` to enable deleting configuration values
* `inizer get-section` to enable reading out entire config sections
* `inizer get-all` to enable reading out entire config files

Tentative planned features include:

* Configuration to enable customizing print and write behavior
* Alternatively, compile-time configuration of alternative parsing backends

## Notes

While it is hoped that inizer is useful for a wide variety of projects and use cases, it currently does not attempt to exceed the capabilities or assumptions of the GLib GKeyFile model. Among other constraints, this entails that inizer

* does not print spaces around quotation marks when saving .ini files
* does not encapsulate configuration values in quotation marks

If these constraints break your configuration files, then inizer is not a suitable solution for your configuration needs at this time. Alternative parsing methods will be considered in the future, but note that existing library solutions such as [iniparser](https://gitlab.com/iniparser/iniparser) and [inih](https://github.com/benhoyt/inih)* were actively investigated and deemed not a fit for use with inizer.

inizer is built on GLib and hence is likely not an ideal first choice for an embedded solution. It primarily targets scripted and automated use cases for desktop users.

\* However, these are both excellent libraries unto themselves and may serve your needs if you're seeking a library to integrate into your own ini-handling solution

## Licensing

inizer is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

inizer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with inizer. If not, see http://www.gnu.org/licenses/.
