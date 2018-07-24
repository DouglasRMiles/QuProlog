// stream_escapes.h - I/O stream manipulations.
//
// ##Copyright##
// 
// Copyright 2000-2016 Peter Robinson  (pjr@itee.uq.edu.au)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.00 
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ##Copyright##
//
// $Id: stream_escapes.h,v 1.3 2002/12/13 00:19:55 qp Exp $

#ifndef	STREAM_ESCAPES_H
#define	STREAM_ESCAPES_H

public:
//
// psi_get_open_streams(StreamList)
// Make a list of all the open stream nums.
//
ReturnValue psi_get_open_streams(Object *&);

//
// psi_open(file, iomode, var)
// Open the file for the specified mode.
//
ReturnValue psi_open(Object *&, Object *&, Object *&);

//
// psi_open_string(string, iomode, type, variable)
// Open a string stream.
//
ReturnValue psi_open_string(Object *&, Object *&, Object *&, Object *&);

//
// psi_close(stream, force)
// Close the specified stream.
//
ReturnValue psi_close(Object *&, Object *&);

//
// psi_current_input(variable)
// Return the current input stream index.
//
ReturnValue psi_current_input(Object *&);

//
// psi_current_output(variable)
// Return the current output stream index.
//
ReturnValue psi_current_output(Object *&);

//
// psi_set_input(stream)
// Switch current input stream to the new index.
//
ReturnValue psi_set_input(Object *&);

//
// psi_set_output(stream)
// Switch current output stream to the new index.
//
ReturnValue psi_set_output(Object *&);

//
// psi_flush_output(stream)
// Flush the output stream.
//
ReturnValue psi_flush_output(Object *&);

//
// psi_set_autoflush(stream)
// Set the output stream to be unbuffered - i.e. flushes at each output.
//
ReturnValue psi_set_autoflush(Object *&);

//
// psi_at_end_of_stream(stream)
// Succeed if the input stream reaches the end of the stream.
//
ReturnValue psi_at_end_of_stream(Object *&);

//
// psi_past_end_of_stream(stream)
// Succeed if the input stream passes the end of the stream.
//
ReturnValue psi_past_end_of_stream(Object *&);

//
// psi_reset_stream(stream)
// Reset the input stream.
//
ReturnValue psi_reset_stream(Object *&);

//
// psi_stream_position(stream, variable)
// Get the stream position.
//
ReturnValue psi_stream_position(Object *&, Object *&);

//
// psi_set_stream_position(stream, position)
// Set the stream to the specified absolute position.
//
ReturnValue psi_set_stream_position(Object *&, Object *&);

//
// psi_line_number(stream, variable)
// Get the line number.
//
ReturnValue psi_line_number(Object *&, Object *&);

//
// psi_stdin(stream)
// Gets the stream associated with standard input.
//
ReturnValue psi_stdin(Object *&);

//
// psi_stdout(stream)
// Gets the stream associated with standard output.
//
ReturnValue psi_stdout(Object *&);

//
// psi_stderr(stream)
// Gets the stream associated with standard error.
//
ReturnValue psi_stderr(Object *&);

//
// psi_open_msgstream(address, iomode, variable)
// Open a message stream.
//
ReturnValue psi_open_msgstream(Object *&, Object *&, Object *&);

//
// psi_set_stream_properties(stream, properties)
// Set the stream properties.
// mode (in,in)
//
ReturnValue psi_set_stream_properties(Object *&, Object *&);

//
// psi_get_stream_properties(stream, properties)
// Get the stream properties.
// mode (in,out)
//
ReturnValue psi_get_stream_properties(Object *&, Object *&);

//
// set_std_stream(stdstream, newstream)
// replace the stream with number stdstream (0,1,2) with newstream.
// mode (in,in)
//
ReturnValue psi_set_std_stream(Object *& , Object *& );

//
// reset_std_stream(stdstream)
// reset the stream with number stdstream (0,1,2).
// mode (in,in)
//
ReturnValue psi_reset_std_stream(Object *& );

#endif
