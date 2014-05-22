<?
if(isset($results) && count($results) > 1):
?>  
    <div id="portfolio">
        <table class="table table-bordered table-hover">
            <tr>
                <th>Name</th>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Current Price (USD)</th>
                <th>Current Value (USD)</th>
            </tr>
            <tbody class="table-striped">
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
        ?>
            </tbody>
        </table>
    </div>
<?
endif;
?>
<div>Total portfolio value: <?= numberFormat($results["balance"]) ?> </div>
<div>Total cash available: <?= numberFormat($cashBalance) ?></div>