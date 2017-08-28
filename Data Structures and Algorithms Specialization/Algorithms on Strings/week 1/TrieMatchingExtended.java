import java.io.*;
import java.util.*;

class Node {
    public static final int Letters = 4;
    public static final int NA = -1;
    public int next[];
    public boolean end;

    Node() {
        next = new int[Letters];
        Arrays.fill(next, NA);
    }

    public boolean isLeaf() {
    	return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA );
    }

   public boolean isEndOfPattern() {
	   return end;
   }
}

public class TrieMatchingExtended implements Runnable {
    int letterToIndex(char letter) {
        switch (letter) {
            case 'A':
                return 0;
            case 'C':
                return 1;
            case 'G':
                return 2;
            case 'T':
                return 3;

            default:
                assert (false);
                return Node.NA;
        }
    }

    List<Node> patternsToTrie(List<String> patterns) {
        List<Node> trie = new ArrayList<>();
        trie.add(new Node());

        for (String pattern : patterns) {
            Node currentNode = trie.get(0);
            for (int i = 0; i < pattern.length(); i++) {
                Character currentSymbol = pattern.charAt(i);
                int index = currentNode.next[letterToIndex(currentSymbol)];

                if (index != Node.NA) {
                    currentNode = trie.get(index);
                } else {
                    Node newNode = new Node();
                    trie.add(newNode);
                    currentNode.next[letterToIndex(currentSymbol)] = trie.size() - 1;
                    currentNode = newNode;
                }
             if (i== pattern.length()-1)currentNode.end=true;
            }

        }
        return trie;
    }

    List<Integer> solve(String text, int n, List<String> patterns) {
        List<Integer> result = new ArrayList<Integer>();
        List<Node> trie = patternsToTrie(patterns);
        int count = 0;
        while (!text.isEmpty()) {
            int match = prefixTrieMatching(text, trie);
            if (match != -1) result.add(count);
            count++;
            text = text.substring(1);
        }
        return result;
    }

    int prefixTrieMatching(String text, List<Node> trie) {
        Character currentSymbol = text.charAt(0);
        Node currentNode = trie.get(0);
        int indexCurrentChar = 0;
        while (true) {
            if (currentNode.isEndOfPattern())  return 1;
             else if (currentNode.next[letterToIndex(currentSymbol)] != Node.NA) {
                currentNode = trie.get(currentNode.next[letterToIndex(currentSymbol)]);
                if (indexCurrentChar + 1 < text.length()) {
                    currentSymbol = text.charAt(++indexCurrentChar);
                } else {
                    if (currentNode.isEndOfPattern())return 1;
                    break;
                }
            }
             else break;
        }
        return -1;
    }


    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
            String text = in.readLine();
            int n = Integer.parseInt(in.readLine());
            List<String> patterns = new ArrayList<String>();
            for (int i = 0; i < n; i++) {
                patterns.add(in.readLine());
            }

            List<Integer> ans = solve(text, n, patterns);

            for (int j = 0; j < ans.size(); j++) {
                System.out.print("" + ans.get(j));
                System.out.print(j + 1 < ans.size() ? " " : "\n");
            }
        } catch (Throwable e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static void main(String[] args) {
        new Thread(new TrieMatchingExtended()).start();
    }


}
