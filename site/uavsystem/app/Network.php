<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Network extends Model
{
    public function uav()
    {
        return $this->belongsTo(Uav::class);
    }
}
