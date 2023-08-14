import java.io.*;
import java.util.*;

public class Crivo {
    public static class Sieve {
        boolean comp[];
        Sieve(int n) {
            comp = new boolean[n + 1];
            for(int i = 2; i <= n; i++) {
                if(comp[i] == false) {
                    for(int j = i * i; j <= n; j += i) {
                        comp[j] = true;
                    }
                }
            }
        }
        boolean isprime(int x) {
            return comp[x] == false;
        }
    }
    public static void main(String[] args) throws IOException {
        FastReader s = new FastReader();
        PrintWriter out = new PrintWriter(System.out);
        int n = s.nextInt();
        Sieve sieve = new Sieve(n);
        for(int i = 2; i <= n; i++) {
            out.println(i + " " + sieve.isprime(i));
        }
        out.flush();
    }
    public static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        public String next() throws IOException {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }

        String nextLine() throws IOException {
            String str = "";
            if (st != null && st.hasMoreTokens()) {
                str = st.nextToken("\n");
            } else {
                str = br.readLine();
            }
            return str;
        }

        int[] nextArrayInt(int n) throws IOException {
            int[] arr = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = nextInt();
            }
            return arr;
        }

        long[] nextArrayLong(int n) throws IOException {
            long[] arr = new long[n];
            for (int i = 0; i < n; i++) {
                arr[i] = nextLong();
            }
            return arr;
        }

        double[] nextArrayDouble(int n) throws IOException {
            double[] arr = new double[n];
            for (int i = 0; i < n; i++) {
                arr[i] = nextDouble();
            }
            return arr;
        }

        String[] nextArrayString(int n) throws IOException {
            String[] arr = new String[n];
            for (int i = 0; i < n; i++) {
                arr[i] = next();
            }
            return arr;
        }

        char[] nextArrayChar() throws IOException {
            return next().toCharArray();
        }

        static void shuffleArray(int[] ar) {
            Random rnd = new Random();
            for (int i = ar.length - 1; i > 0; i--) {
                int index = rnd.nextInt(i + 1);
                int a = ar[index];
                ar[index] = ar[i];
                ar[i] = a;
            }
        }

        static void shuffleArray(long[] ar) {
            Random rnd = new Random();
            for (int i = ar.length - 1; i > 0; i--) {
                int index = rnd.nextInt(i + 1);
                long a = ar[index];
                ar[index] = ar[i];
                ar[i] = a;
            }
        }

        public int[] nextSortedArrayInt(int n) throws IOException {
            int[] arr = nextArrayInt(n);
            shuffleArray(arr);
            Arrays.sort(arr);
            return arr;
        }

        public long[] nextSortedArrayLong(int n) throws IOException {
            long[] arr = nextArrayLong(n);
            shuffleArray(arr);
            Arrays.sort(arr);
            return arr;
        }
    }
}
