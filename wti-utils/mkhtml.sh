#!/bin/bash
for file in [A-O]-*
do
        echo "<tr>"
        echo ' <td><a href="'problems/$file/$file.pdf'">'$file'</a> </td>'
        echo ' <td><a href="'problems/$file/sample'">Sample Input/Output</a> </td>'
        echo "</tr>"
done

