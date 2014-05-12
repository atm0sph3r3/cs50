<table>
    <tr><th>Name</th><th>Symbol</th><th>Shares</th><th>Current Price</th><th>Current Value</th></tr>
<?php
$totalValue = 0;
if(isset($results) && count($results) > 0){
    $decimalPlaces = 3;
    foreach($results as $result){
        $shares = $result["shares"];
        $price = $result["price"];
        $value = $shares * $price;
        $totalValue += $value;
        print("<tr>");
        print("<td>{$result["name"]}</td>");
        print("<td>{$result["symbol"]}</td>");
        print("<td>{$shares}</td>");
        print("<td>".number_format($price, $decimalPlaces)."</td>");
        print("<td>".number_format($value, $decimalPlaces)."</td>");
        print("</tr>");
    }
    print("</table>");
} else {
    print("<div>No stocks to display.");
}
print("<div>Total portfolio value:{$totalValue} ")
?>
</table>