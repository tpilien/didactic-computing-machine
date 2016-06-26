#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <bits/stdc++.h>

struct Share {
    int buy;
    int profit;
};

struct Pack {
    int buy;
    int profit;
};

std::unordered_map<long long, long long[100]> table;
//
//std::vector<Pack> packList;
Pack packList[100];

long long count(int i, long long j) {
    if (i < 0) return 0;
    if (table[j][i]) {
        return table[j][i];
    }
    if (j < packList[i].buy) {
        return table[j][i] = count(i-1, j);
    }
    return table[j][i] = std::max(packList[i].profit + count(i-1, j - packList[i].buy), count(i-1, j));
}

int main() {
    int money;
    int lol;
    std::cin >> money;
    while (1) {
        int shares, packs, buy, sell;
        //std::cin >> shares >> packs;
        lol = scanf("%d %d", &shares, &packs);
        Share shareList[shares + 1];
        int psize = 0;        
        for (int i = 0; i < shares; ++i) {
            lol = scanf("%d %d", &buy, &sell);
//            std::cin >> buy >> sell;
            shareList[i+1] = {buy, sell - buy};
        }

        for (int i = 0; i < packs; ++i) {
            int packSize;
            lol = scanf("%d", &packSize);
            int shareNum, shareQty;            
            Pack p = {0, 0};
            for (int j = 0; j < packSize; ++j) {

                lol = scanf("%d %d", &shareNum, &shareQty);
                p.buy += shareList[shareNum].buy * shareQty;
                p.profit += shareList[shareNum].profit * shareQty;
            }
            if (p.profit > 0 && p.buy <= money) {
                packList[psize++] = p;
            }
            
        }
        
        table.clear();
        std::cout << count(psize, money) << std::endl;
        if (std::cin >> money) {
            std::cout << std::endl;
        } else {
            break;
        }
    }
    return !lol;
}
