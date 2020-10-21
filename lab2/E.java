import java.io.*;
import java.util.*;

public class RadixSort {
    String fileName = "radixsort";

    String[] a;
    int n;
    ArrayList<String>[] count = new ArrayList[26];

    void radixSort(int d) {
        for (int i = 0; i < 26; i++) {
            count[i] = new ArrayList<>();
        }
        for (int i = 0; i < n; i++) {
            count[a[i].charAt(d) - 'a'].add(a[i]);
        }
        int cnt = 0;
        for (int i = 0; i < 26; i++) {
            for (String j : count[i]) {
                a[cnt] = j;
                cnt++;
            }
        }
    }

    public void solve() throws IOException {
        n = nextInt();
        int m = nextInt();
        int k = nextInt();
        a = new String[n];
        for (int i = 0; i < n; i++) {
            a[i] = nextToken();
        }
        for (int i = 0; i < k; i++) {
            radixSort(m - i - 1);
        }
        for (int i = 0; i < n; i++) {
            out.println(a[i]);
        }
    }

    public void run() {
        try {
            if ("".equals(fileName)) {
                br = new BufferedReader(new InputStreamReader(System.in));
                out = new PrintWriter(System.out);
            } else {
                br = new BufferedReader(new FileReader(fileName + ".in"));
                out = new PrintWriter(fileName + ".out");
            }
            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        new RadixSort().run();
    }

}