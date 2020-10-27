#ifndef RECORD_H
#define RECORD_H

#include <memory>

class record {
	private:
		std::unique_ptr<char[]> name;
		int phone = -1;
		int group = -1;

	public:
		record() = default;
		~record() = default;

		char * get_name() const { return name.get(); }
		int get_phone() const { return phone; }
		int get_group() const { return group; }

		int operator==(const record &) const;
		int operator!=(const record &) const;

		void init(record &);
		int read(FILE *);
		void print(FILE *fp = stdout) const;

		static int name_cmp(const record &, const record &);
		static int phone_cmp(const record &, const record &);
		static int group_cmp(const record &, const record &);

	friend class command;
};

#endif // RECORD_H
