<?
if($results !== FALSE):
?>
    <table>
        <tr>
            <th>Date</th>
            <th>Transaction Type</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
<?
    foreach($results as $transaction){
        print("<tr>");
        print("<td>".date("r",$transaction["date"])."</td>");
        print("<td>{$transaction["type"]}</td>");
        print("<td>{$transaction["symbol"]}</td");
        print("<td>{$transaction["shares"]}</td>");
        print("<td>".numberFormat($transaction["price"])."</td>");
        print("</tr>");
    }
    print("</table>");
    endif;
?>