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

        <form method="POST" action="sell.php">
            <fieldset>
                <?
                while($result = current($results)){
                    if(key($results) !== "balance"){
                        print("<tr>");
                        print("<td><input type = 'checkbox' name = {$result["symbol"]}></td>");
                        print("<td>{$result["name"]}</td>");
                        print("<td>{$result["symbol"]}</td>");
                        print("<td>{$result["shares"]}</td>");
                        print("<td>".numberFormat($result["price"])."</td>");
                        print("<td>".numberFormat(($result["price"] * $result["shares"]))."</td>");
                        print("</tr>");
                    }
                    next($results);
                }
                ?>
    </table>
    <div>
        <input type="submit">
        <input type="reset">
    </div>
            </fieldset>
        </form>
<? else : ?>
    <div>
        No results to display
    </div>
<? endif;

