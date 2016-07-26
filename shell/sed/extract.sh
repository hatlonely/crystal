cat text.txt | sed -n /line1/,/line5/p | sed /line1/d | sed /line2/d
