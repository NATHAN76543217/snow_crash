#!/usr/bin/php
<?php
    function y($m) {
        print "Y - " . $m;
        $m = preg_replace("/\./", " x ", $m);
        $m = preg_replace("/@/", " y", $m);
        return $m;
    }

    function x($y, $z) {
        $a = file_get_contents($y);
        print "A - " . $a . "\n";
        $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
        print "B - " . $a . "\n";
        $a = preg_replace("/\[/", "(", $a);
        print "C - " . $a . "\n";
        $a = preg_replace("/\]/", ")", $a);
        print "D - " . $a . "\n";
        return $a;
    }
    $r = x($argv[1], $argv[2]);
    print $r;
?>
