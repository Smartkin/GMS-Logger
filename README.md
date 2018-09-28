## Logger
> Simple logger library for GameMaker: Studio

## Description
	The library is made in C++ for GameMaker: Studio(GMS) but surely can be used in other applications if so desired. But because of certain GMS contraints, some things had to be done in a way that probably shouldn't have been done.

# Features
	The logger is quite simple, you choose one of the few currently available options "Append","Date","Severity" they are flags which means that they can be combined.
	* Append - default flag though useless for now
	* Date - whether the message you log gets a date printed next to it
	* Severity - whether the message you log gets a severity type printed next to it
	The available severity types are "Trace","Information","Debug","Warning","Error".

# API
	The API calls are simple and can all be found in API.cpp

# Compiling
	Library can be compiled using VisualStudio 2017(2015 might work too)