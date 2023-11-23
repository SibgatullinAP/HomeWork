# F. Полиглоты

def task():
    N = int(input())
    pupils_languages = []
    for _ in range(N):
        language_count = int(input())
        languages = set()
        for lang_ind in range(language_count):
            languages |= set([input()])
        #assert len(languages) == language_count
        pupils_languages.append(languages)

    well_known_languages = pupils_languages[0]
    known_languages = set()
    for pupil_languages in pupils_languages:
        well_known_languages &= pupil_languages
        known_languages |= pupil_languages

    print (len(well_known_languages))
    print ('\n'.join(well_known_languages))
    print(len(known_languages))
    print('\n'.join(known_languages))


task()
