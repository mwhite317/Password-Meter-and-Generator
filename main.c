#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h> // used for testing in main
#include <time.h>
#include <stdlib.h>

bool isStrongPassword(const char *username, const char *password);

bool isAtLeast8(const char *password);

bool containsUpper(const char *password);

bool containsLower(const char *password);

bool containsDigit(const char *password);

bool containsOnlyPermittedChar(const char *password);

bool containsConsecutivesStr(const char *password);

bool containsUsername(const char *username, const char *password);

bool isDigit(const char password);

bool isLower(const char password);

bool isUpper(const char password);

bool containsSubstring(const char *string1, const char *string2);

void toLower(char *original, char *lowered);

void generateDefaultPassword(char *default_password, const char *username);

bool isStrongDefaultPassword(const char *username, const char *password);

bool noMoreThan15(const char *password);

int main() {
    char *tooShort = "1234567";
    char *longenough = "12345678";
    assert(!isAtLeast8(tooShort));
    assert(isAtLeast8(longenough));

    char *allLower = "lowercase";
    char *allUpper = "UPPERCASE";
    char *singleUpper = "uppercasE";
    assert(!containsUpper(allLower));
    assert(containsUpper(allUpper));
    assert(containsUpper(singleUpper));

    char *singleLower = "LOWERCASe";
    assert(containsLower(allLower));
    assert(!containsLower(allUpper));
    assert(containsLower(singleLower));

    char *allnumbers = "1234567890";
    char *oneNumber = "UPPERCASE1";
    char *noNum = allLower;
    assert(!containsDigit(noNum));
    assert(containsDigit(allnumbers));
    assert(containsDigit(oneNumber));

    char *permited = "LKlk23sd32W";
    char *onePermitted = "J!@#$@";
    char *notPermitted = "!@#$%^&*(";
    assert(containsOnlyPermittedChar(permited));
    assert(!containsOnlyPermittedChar(onePermitted));
    assert(!containsOnlyPermittedChar(notPermitted));

    char *trickster = "999dfs0000asg00";
    char *endString = "999dfs0000asga";
    assert(containsConsecutivesStr(permited));
    assert(!containsConsecutivesStr(allnumbers));
    assert(!containsConsecutivesStr(trickster));
    assert(containsConsecutivesStr(endString));

    char *pwrd = "abc";
    char *nope = "sss";
    char *yes = "hmabc";
    assert(!containsSubstring(nope, pwrd));
    assert(containsSubstring(pwrd, yes));

    char lowered[30];
    toLower(allUpper, lowered);
    assert(strcmp(lowered, "uppercase") == 0);

    char *user = "vahab";
    char *password = "123vaHaBk789";
    char *password2 = "123va789";
    assert(containsUsername(user, password));
    assert(!containsUsername(user, password2));

    char *username = "vahab";
    char *notStrong = "1234";
    char *notStrong2 = "hello";
    char *notStrong3 = "123vaHaBk789";
    char *strong = "meAceCS221";
    assert(!isStrongPassword(username, notStrong));
    assert(!isStrongPassword(username, notStrong2));
    assert(!isStrongPassword(username, notStrong3));
    assert(isStrongPassword(username, strong));

    char *generatePassword = "x1B4fxH81I02";
    char *tooLong = "x1B4fxH81I02x1B4fxH81I02x1B4fxH81I02";
    assert(isStrongDefaultPassword(username, generatePassword));
    assert(!isStrongDefaultPassword(username, tooLong));

    assert(isStrongDefaultPassword(username, "LcvMro1kZLMldVH"));

    char default_password[15];
    generateDefaultPassword(default_password, username);
    assert(isStrongDefaultPassword(username, default_password));

    return 0;

}

void generateDefaultPassword(char *default_password, const char *username) {
    srand(time(NULL)); // used to select different ascii numbers
    while (!isStrongDefaultPassword(username, default_password)) {
        for (int i = 0; i < 14; ++i) {
            int randomChar = rand() % 122; // randomly pulls a ascii value
            while (!(isDigit(randomChar) || isLower(randomChar) ||
                     isUpper(randomChar))) { // if not a digit or letter, then pulls another value
                randomChar = rand() % 122;
            }
            default_password[i] = randomChar; // added ascii value to string
        }
        printf("%s\n", default_password); // prints rather then returns since it is a void function
    }
}

/*
 * Similar to isStrongPassword but changed 2 conditions:
 * added noMoreThan15()
 * deleted containsConsecutiveStr()
 */
bool isStrongDefaultPassword(const char *username, const char *password) {
    return noMoreThan15(password) // generated password can be more no more than 15 characters
           && isAtLeast8(password)
           && containsUpper(password)
           && containsLower(password)
           && containsDigit(password)
           && containsOnlyPermittedChar(password)
           && !containsUsername(username, password);
}

/*
 * Meets all the requirements to have a strong password
 */
bool isStrongPassword(const char *username, const char *password) {
    return isAtLeast8(password)
           && containsUpper(password)
           && containsLower(password)
           && containsDigit(password)
           && containsOnlyPermittedChar(password)
           && containsConsecutivesStr(password)
           && !containsUsername(username, password); // check that password does NOT contain username
}

/*
 * checks string length is at least 8
 */
bool isAtLeast8(const char *password) {
    return (strlen(password) >= 8);
}

/*
 *  checkds that the string length is no more than 15
 */
bool noMoreThan15(const char *password) {
    return (strlen(password) <= 15);
}

/*
 * Checks that the character is in between A and Z
 */
bool isUpper(const char password) { return password >= 'A' && password <= 'Z'; }

/*
 * Searches through password and checks that one character is uppercase using isUpper()
 */
bool containsUpper(const char *password) {
    while (*password != '\0') {
        if (isUpper(*password)) {
            return true;
        }
        ++password;
    }
    return false;

}

/*
 * Checks that the character is in between a and z
 */
bool isLower(const char password) { return password >= 'a' && password <= 'z'; }

/*
 * Searches through password and checks that one character is lowercase using isLower()
 */
bool containsLower(const char *password) {
    while (*password != '\0') {
        if (isLower(*password)) {
            return true;
        }
        ++password;
    }
    return false;
}

/*
 * Checks character is between 0 and 9
 */
bool isDigit(const char password) { return password >= '0' && password <= '9'; }

/*
 * Searches through password and checks that one character is a digit using isdigit()
 */
bool containsDigit(const char *password) {
    while (*password != '\0') {
        if (isDigit(*password)) {
            return true;
        }
        ++password;
    }
    return false;
}

/*
 * Checks password contains only digits, and letters
 */
bool containsOnlyPermittedChar(const char *password) {
    while (*password != '\0') {
        if (!(isDigit(*password) || isLower(*password) || isUpper(*password))) { // uses or operators for efficiency
            return false;
        }
        ++password;
    }
    return true;
}

/*
 * Checks that password has at least 4 consecutive letters
 */
bool containsConsecutivesStr(const char *password) {
    int currentLength = 0;
    while (*password != '\0') {
        if ((isLower(*password) || isUpper(*password))) { // can be uppercase OR lowercase
            currentLength++; // update length
            if (currentLength == 4) {
                return true;
            }
        } else {
            currentLength = 0;
        }
        ++password;
    }
    return false;
}

/*
 * Checks that password has no username
 */
bool containsUsername(const char *username, const char *password) {
    char loweredUsername[strlen(username)];
    toLower(username, loweredUsername); // need to make username all lowercase for comparision

    char loweredPassword[strlen(password)];
    toLower(password, loweredPassword); // need to make password all lowercase for comparision

    bool contains = containsSubstring(loweredUsername,
                                      loweredPassword); // compares lowercase username and lowercase password
    return contains;
}

/*
 * Takes the original char or string and assigns to lowered before making lowered lowercase
 */
void toLower(char *original, char *lowered) {

    while (*original != '\0') {

        if (isUpper(*original)) {
            *lowered = *original + 32; // difference between A and a in ascii table
        } else {
            *lowered = *original;
        }
        lowered++;
        original++;
    }
    *lowered = '\0';
}

/*
 * Checks if string1 contains the string2 inside the string1
 */
bool containsSubstring(const char *string1, const char *string2) {
    int len1 = strlen(string1);
    int len2 = strlen(string2);

    for (int i = 0; i <= len2 - len1; ++i) {
        int j;
        for (j = 0; j < len1; ++j) {
            if (string2[i + j] != string1[j]) {
                break;
            }

        }
        if (j == len1) {
            return true;

        }
    }
    return false;
}