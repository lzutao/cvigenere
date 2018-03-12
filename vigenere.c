/**
 * Program: vigenere.c
 * Function: encode and decode a vigenere string with given key
 * Supported charset: [a-z]
 */

#include "vigenere.h"

void
usage(char const *program_name, bool shortmenu);

void
fatal_error(char const *fmt, ...);

void
make_shitfarray(char *out, char const *key, size_t key_len);

const size_t NUMLETTERS = 26;

enum MODE_T { ENCODE_MODE, DECODE_MODE };  // Default set

int
main(int argc, char * const *argv)
{
	int opt = 0;
	enum MODE_T mode = ENCODE_MODE;
	char *key = NULL;
	while ((opt = getopt(argc, argv, "hedk:")) != -1) {
		switch (opt) {
		case 'e': mode = ENCODE_MODE; break;
		case 'd': mode = DECODE_MODE; break;
		case 'k': key = optarg; break;
		case 'h':
		default: /* '?' */
			usage(argv[0], false);
		}
	}
	if (optind >= argc) {
		fatal_error("too few arguments");
		usage(argv[0], true);
	}

	char const *source = argv[optind];
	size_t src_len = strlen(source);

	size_t key_len = strlen(key);
	char shifts[key_len];
	make_shitfarray(shifts, key, key_len);

	char result[src_len + 1];

	switch (mode) {
	case DECODE_MODE:
		vigenereDecode(result, source, shifts, key_len);
		printf("Plaintext : %s\n", result);
		break;
	case ENCODE_MODE:
		vigenereEncode(result, source, shifts, key_len);
		printf("Ciphertext: %s\n", result);
		break;
	default:
		fatal_error("parsing mode var.");
	}

	return 0;
}

int
mod(int dividend, int divisor) {
	int modulus = dividend % divisor;
	return (modulus >= 0) ? modulus : abs(divisor) + modulus;
}

char
caesarEncode(char token, int shift) {
	char charcase = isupper(token) ? 'A' : 'a';
	return mod(token - charcase + shift, NUMLETTERS) + charcase;
}

int
vigenereEncode(char *result, char const *source, char const *shiftarray, size_t shift_size) {
	const size_t src_len = strlen(source);
	size_t i = 0;
	// Only process alphabetical characters
	for (; i < src_len; ++i) {
		if (isalpha(source[i])) {
			result[i] = caesarEncode(source[i], shiftarray[i % shift_size]);
		}
		else
			result[i] = source[i];
	}

	result[i] = '\0';
	return 0;
}

int
vigenereDecode(char *result, char const *source, char const *shiftarray, size_t shift_size) {
	char shifts[shift_size];
	size_t i = 0;

	for (; i < shift_size; ++i) {
		shifts[i] = -shiftarray[i];
	}

	vigenereEncode(result, source, shifts, shift_size);
	return 0;
}

void
usage(char const *program_name, bool shortmenu) {
	fprintf(stderr, "Usage: %s [-h] [-e | -d] -k KEY message\n", program_name);
	if (!shortmenu) {
		fprintf(stderr,"Vigenere Cipher - encode, decode messages polyalphabetic cipher.\n"
			"\n"
			"positional arguments:\n"
			"  message    ASCII message to be encoded, decoded. Note that also accepts space character.\n"
			"\n"
			"optional arguments:\n"
			"  -h,        show this help message and exit.\n"
			"  -k KEY     ASCII string consists of alphabetical characters only, no punctuation or number.\n"
			"  -e,        encodes the message.\n"
			"  -d,        decodes the message.\n"
			"\n"
			"[+] Written by 15520599\n");
	}
	exit(EXIT_FAILURE);
}

void
fatal_error(char const *fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	fprintf(stderr, "Error: ");
	vfprintf(stderr, fmt, argptr);
	fprintf(stderr, "\n");
	va_end(argptr);
}


void
make_shitfarray(char *out, char const *key, size_t key_len) {
	char charcase;
	for (size_t i = 0; i < key_len; ++i) {
		if (!isalpha(key[i])) {
			fatal_error("Invalid key");
		}
		// equivalent to function tolower()
		charcase = isupper(key[i]) ? 'A' : 'a';
		out[i] = key[i] - charcase;
	}
}