<?php if(!empty($result['nodes'])) { ?>
<div class="clearfix">
    <table class="table table-bordered column_small white">
        <thead>
            <tr>
                <th>The Comedy Club - Latest/Updated <?php echo $result['node_type']->name; ?></th>
            </tr>
        </thead>
        <tbody>
            <?php

            foreach($result['nodes'] as $item) { ?>

            <tr><td>

                <a href="<?php echo $item[1]; ?>" class="bootstrap_title" 
            title="<?php echo 'Click to View'; ?>" 
            data-original-title="<?php 'Click to View'; ?>"><?php echo substr($item[0], 0, 30); ?></a>

            </td>

            <?php }
            ?>
        </tbody>
    </table>
</div>
<?php } ?>