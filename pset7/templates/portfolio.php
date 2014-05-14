<?
if(isset($results) && count($results) > 0):
?>
    <table>
        <tr>
            <th>Name</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Current Price</th>
            <th>Current Value</th>
        </tr>
<?
    while($result = current($results)){
        if(key($results) !== "balance"){
            print("<tr>");
            print("<td>{$result["name"]}</td>");
            print("<td>{$result["symbol"]}</td>");
            print("<td>{$result["shares"]}</td>");
            print("<td>".numberFormat($result["price"])."</td>");
            print("<td>".numberFormat($result["value"])."</td>");
            print("</tr>");
        }
        next($results);
    }
    print("</table>");
    print("<div>Total portfolio value: ".numberFormat($results["balance"])."</div>");
    print("<div>Total cash available: ".numberFormat($cashBalance)."</div>");
else:
    print("<div>No stocks to display.");
endif;
?>