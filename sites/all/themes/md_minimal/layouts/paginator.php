<div class="pagination pagination-small clearfix">
    <div class="pull-right">
        <?php $span = ($count % $length !== 0) ? (int) ($count / $length + 1) : $count / $length; ?>
        <span id="paginator_description" class="pull-left white">Page <span id="paginator_page_number"><?php echo $page; ?></span> of <span id="paginator_page_count"><?php echo $span; ?></span> :</span>
        <span class="pull-left">&nbsp;&nbsp;</span>
        <div class="pull-left">
            <span>Move to Page: </span>
            <select id="paginator_select" name="pagination-page" style="width:50px">
                <?php
                for($num = 1; $num <= $span; $num++) { ?>
                    <option <?php echo ($page == $num) ? 'selected="true"' : '' ?> value="<?php echo $num; ?>"><?php echo $num; ?></option>
                <?php }
                ?>
            </select>
        </div>
        <span class="pull-left">&nbsp;&nbsp;</span>
        <div class="pull-left"><ul>
            <li id="paginator_previous" class="<?php echo $li_prev; ?>"><a style="cursor:pointer" class="<?php echo $li_prev; ?>" href="<?php echo $prev; ?>"> &lt;&lt; </a></li>
            <li id="paginator_next" class="<?php echo $li_next; ?>"><a style="cursor:pointer" class="<?php echo $li_next; ?>" href="<?php echo $next; ?>"> &gt;&gt; </a></li>
        </ul></div>
    </div>
</div>