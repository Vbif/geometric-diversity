//
//  NSData+Base64.h
//  base64
//
//  Created by Matt Gallagher on 2009/06/03.
//  Copyright 2009 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file, free of charge, in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//

#ifdef __OBJC__
#import <Foundation/Foundation.h>

@interface NSData (Base64)

+ (NSData *)dataFromBase64String:(NSString *)aString;
- (NSString *)base64EncodedString;

@end
#endif

size_t Base64DecodedLength(size_t inputLength);
size_t Base64EncodedLength(size_t inputLength);

size_t Base64Decode(const char* inputBuffer, size_t length, char* outputBuffer);
size_t Base64Encode(const char* inputBuffer, size_t length, char* outputBuffer);
