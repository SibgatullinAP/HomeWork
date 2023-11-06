# J. Числа Фибоначчи
def task_h():
    n = int(input())
    if n < 0:
        raise Exception()

    var_phi_prev_prev = 0
    if n == 0:
        print(var_phi_prev_prev)
        return

    var_phi_prev = 1
    if n == 1:
        print(var_phi_prev)
        return

    var_phi_curr = var_phi_prev_prev + var_phi_prev
    for i in range (2, n + 1):
        var_phi_curr = var_phi_prev_prev + var_phi_prev
        var_phi_prev_prev = var_phi_prev
        var_phi_prev = var_phi_curr

    print(var_phi_curr)


task_h()
