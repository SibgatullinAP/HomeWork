#include <stdio.h>
#include <string.h>
#include "record.h"
#include "errors.h"

int record::operator==(const record &x) const {
	return (phone == x.phone) && (group == x.group) && !strcmp(name.get(), x.name.get());
}

int record::operator!=(const record &x) const {
	return (phone != x.phone) || (group != x.group) || strcmp(name.get(), x.name.get());
}

void record::init(record &x){
	name = std::move(x.name);
	phone = x.phone;
	group = x.group;
}

int record::read(FILE *fp){
	char buf[LEN];

	if(fscanf(fp, "%s%d%d", buf, &phone, &group) != 3){
		return feof(fp) ? 1 : ERR_READ;
	}

	name = std::make_unique<char[]>(strlen(buf) + 1);
	if(!name) return ERR_MEMORY;
	strcpy(name.get(), buf);

	return 0;
}

void record::print(FILE *fp) const {
	fprintf(fp, "%s %d %d\n", name.get(), phone, group);
}

int record::name_cmp(const record &r1, const record &r2){
	return strcmp(r1.name.get(), r2.name.get());
}

int record::phone_cmp(const record &r1, const record &r2){
	int n1 = r1.phone, n2 = r2.phone;

	if(n1 == n2) return 0;
	return ((n1 < n2) ? -1 : 1);
}

int record::group_cmp(const record &r1, const record &r2){
	int n1 = r1.group, n2 = r2.group;

	if(n1 == n2) return 0;
	return ((n1 < n2) ? -1 : 1);
}
