<table style="width:100%">
        <thead>
            <tr>
                <th>Device</th>
                <th>Operations</th>
            </tr>
        </thead>
        <tbody>
        @foreach($devices as $device)

            <tr>
                <td>{{$device->name}}</a></td> 
                <td>
                    <div class="form-group">
                        <form action="{{'/devices/'.$device->id }}" method="post">
                            {{ csrf_field() }}
                            {{method_field('DELETE')}}
                            <a href="{{'/devices/'.$device->id.'/edit' }}" class="btn btn-warning"><i class="fa fa-edit"></i></a>
                            <button type="submit" class="btn btn-danger btn-xl">
                            <i class="fa fa-trash"></i>
                            </button>
                        </form>
                    </div>
            </td>
            </tr>
        @endforeach
        </tbody>
    </table>