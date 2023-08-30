def main():
    while True:
        try:
            num = int(input("Card number: "))
        except:
            print("Not a number. Try again")
        else:
            break
    validation = validate(num)
    if validation:
        company = det_company(num)
        if type(company) is str:
            print(company)
            return 0
    print("INVALID")
    return 1


def validate(n): ##Luhn's algorithm
    rev_str_n = str(n)[::-1]
    position = len(rev_str_n)

    product_sum = 0
    not_multiplied_sum = 0

    for d in rev_str_n:
        if (position % 2 == 1 and len(rev_str_n) % 2 == 0) or (position % 2 == 0 and len(rev_str_n) % 2 == 1):
            for x in str(int(d)*2):
                if x != 0:
                    product_sum += int(x)
        else:
            not_multiplied_sum += int(d)
        position -= 1

    final_sum = product_sum + not_multiplied_sum

    if (final_sum % 10 == 0):
        return True
    return False


def det_company(n):
    card_length = len(str(n))
    if card_length == 13 and str(n)[0] == "4": ##VISA
        return "VISA"
    elif card_length == 15 and (str(n)[0:2] in ["34","37"]): ##AMERICAN EXPRESS
        return "AMEX"
    elif card_length == 16: ##VISA OR MASTERCARD
        if str(n)[0] == "4":
            return "VISA"
        elif str(n)[0:2] in ["51","52","53","54","55"]:
            return "MASTERCARD"
    else:
        return

main()