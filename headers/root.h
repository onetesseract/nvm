#pragma once

#ifndef ROOT_H
#define ROOT_H

#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...) /* do nothing in release builds */
#endif

#endif