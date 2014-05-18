<div id="purchaseStock">
    <h2>Purchase Stock</h2>
    <p>Current cash balance: $<?= numberFormat(User::getUser()->cashBalance()) ?></p>
    <form action="buy.php" method="POST">
        <fieldset>
            <div class="form-group">
                <input type="text" class="form-control" maxlength="10" autofocus name="symbol" placeholder="Stock Symbol">
            </div>
            <div class="form-group">
                <input type="text" class="form-control" maxlength="10" name="shares" placeholder="Number of Shares">
            </div>
            <div clas="form-group">
               <button type="submit" class="btn btn-default">Purchase Stock</button>
               <button type="reset" class="btn btn-default">Reset</button>
            </div>
        </fieldset>
    </form>
</div>
