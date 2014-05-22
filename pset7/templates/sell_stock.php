<?
if(isset($results) && count($results) > 1): 
?>
<h2>Sell Stock</h2>
    <table class="table table-bordered table-hover">
        <tr>
            <th>Sell</th>
            <th>Name</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Current Price</th>
            <th>Current Value</th>
        </tr>
        <tbody class="table-striped">
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
            </tbody>
    </table>
    <div>
        <button type="submit" class="btn btn-default">Sell Stock</button>
        <button type="reset" class="btn btn-default">Reset</button>
    </div>
            </fieldset>
        </form>
<? else : ?>
    <div>
        No stocks to sell. Consider buying some!
    </div>
<? endif;

