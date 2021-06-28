int min_int(int a, int b) {
    int a_lt_b_mask = (a - b) >> (sizeof(int) * 8 - 1);
    return (a_lt_b_mask & a) | ((~a_lt_b_mask) & b);
}

int max_int(int a, int b) {
    int a_gt_b_mask = (b - a) >> (sizeof(int) * 8 - 1);
    return (a_gt_b_mask & a) | ((!a_gt_b_mask) & b);
}

