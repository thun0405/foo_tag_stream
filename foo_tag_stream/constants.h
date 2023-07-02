#pragma once

#ifndef CONSTANTS_H
	#define CONSTANTS_H
	// 改行コード
	#ifdef _WIN32
	const char* NEWLINE = "\r\n";
	#else
	const char* NEWLINE = "\n";
	#endif
#endif // CONSTANTS_H