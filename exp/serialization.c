#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define BLOCK 512
typedef uint64_t *buffer;

typedef struct unit_
{
	double x;
	double y;
	double z;
	double t;
}
unit_;

// uint64_t serialize_double(double value)
char *serialize_double(double value)
{
	union
	{
		double f;
		uint64_t i;
	}
	d;
	d.f = value;

    char *b = malloc(sizeof(uint64_t));
    sprintf(b, "%" PRIu64 "\n", value);

	return b;
	// return d.i;
}

double deserialize_double(uint64_t value)
{
	union
	{
		double f;
		uint64_t i;
	}
	d;

	d.i = value;
	return d.f;
}

int serialize_unit_(unit_ *unit, buffer b)
{
	memcpy(b, serialize_double(unit->x), sizeof(uint64_t));
	// memcpy(b, (char*)serialize_double(unit->y), sizeof(uint64_t));
	// memcpy(b, (char*)serialize_double(unit->z), sizeof(uint64_t));
	// memcpy(b, (char*)serialize_double(unit->t), sizeof(uint64_t));

	return 0;
}

unit_ *deserialize_unit_(buffer b)
{
	unit_ *unit = malloc(sizeof(unit_));
	unit->x = b[0];
	unit->y = b[1];
	unit->z = b[2];
	unit->t = b[3];

	return unit;
}

int main()
{
	unit_ *unit = malloc(sizeof(unit_));
	unit->x = 1;
	unit->y = 2;
	unit->z = 3;
	unit->t = 4;

	printf("%f\n", unit->x);
	printf("%f\n", unit->y);
	printf("%f\n", unit->z);
	printf("%f\n", unit->t);

	uint64_t *b = malloc(BLOCK * sizeof(uint64_t));
	char *x = serialize_double((double) 8.126387);

	double d = deserialize_double(x);
	printf("d: %f\n", d);

	serialize_unit_(unit, b);
	printf("buffer: %s", b);
	// unit_ *dunit = deserialize_unit_(b);
	// printf("\n\nde: %f %f %f %f", dunit->x, dunit->y, dunit->z, dunit->t);
	return 0;
}