import java.io.*;
import java.util.*;

public class TSP {
    public static double dist(double x1, double y1, double x2, double y2) {
        return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        double x[] = new double[n], y[] = new double[n];
        for(int i = 1; i < 2 * n + 1; i += 2) {
            x[(i - 1) / 2] = Double.parseDouble(args[i]);
            y[(i - 1) / 2] = Double.parseDouble(args[i + 1]);
        }
        double dp[][] = new double[n][(1 << n)];
        int prv[][] = new int[n][(1 << n)];
        for(int i = 0; i < n; i++) {
            dp[i][(1 << i)] = dist(0, 0, x[i], y[i]);
            prv[i][(1 << i)] = -1;
        }
        for(int mask = 1; mask < (1 << n); mask++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(i == j) continue;
                    if(((mask >> i) & 1) == 1 && ((mask >> j) & 1) == 0) {
                        if(dp[j][(mask | (1 << j))] == 0 || dp[j][(mask | (1 << j))] > dp[i][mask] + dist(x[i], y[i], x[j], y[j])) {
                            dp[j][(mask | (1 << j))] = dp[i][mask] + dist(x[i], y[i], x[j], y[j]);
                            prv[j][(mask | (1 << j))] = i;
                        }
                    }
                }
            }
        }
        double tmp = Double.MAX_VALUE;
        int id = -1;
        for(int i = 0; i < n; i++) {
            if(dp[i][(1 << n) - 1] + dist(0, 0, x[i], y[i]) < tmp) {
                tmp = dp[i][(1 << n) - 1] + dist(0, 0, x[i], y[i]);
                id = i;
            }
        }
        ArrayList<Integer> path = new ArrayList<Integer>();
        int mask = (1 << n) - 1;
        path.add(-1);
        while(id != -1) {
            path.add(id);
            int nid = prv[id][mask];
            mask ^= (1 << id);
            id = nid;
        }
        path.add(-1);
        System.out.println(tmp + " is the total distance.");
        System.out.println("The order of the points:");
        for(int i = 0; i < path.size(); i++) {
            if(path.get(i) == -1) {
                System.out.println("0 0");
            } else {
                System.out.println(x[path.get(i)] + " " + y[path.get(i)]);
            }
        }
    }
}
