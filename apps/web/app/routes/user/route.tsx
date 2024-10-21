/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction } from "@remix-run/node";
import { PageHeader, Button, Input } from "../../components";
// import { useLoaderData } from "@remix-run/react";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to Remix!" },
    ];
};

export async function loader() {
    // const resp = await fetch("https://api.unsplash.com/photos?per_page=1000", {
    //     headers: { Authorization: `Client-ID ${process.env.UNSPLASH_ACCESS_KEY}` },
    // });

    // if (resp.ok) return { photos: await resp.json() };
    // else return { photos: [] };
    return null
}

export default function Account() {
    // const { photos } = useLoaderData<typeof loader>();

    return (
        <div className="flex items-center justify-center h-full">
            <div className="flex flex-col items-center gap-8 h-full">
                <PageHeader />

                <h2 className="text-2xl font-black ">User Account</h2>

                <div className="flex flex-col gap-4 p-4">
                    <h3 className="text-xl">Change password</h3>
                    <form className="flex flex-col gap-4 p-4">
                        <Input type="password" id="password" name="password" placeholder="Enter new password" />
                        <Input type="password" id="confirm-password" name="confirm-password" placeholder="Confirm new password" />
                        <Button type="submit">Change Password</Button>
                    </form>
                </div>

                <div className="flex flex-col gap-4 p-4">
                    <h3 className="text-xl">Invites</h3>
                    <p> You have 1 invite left</p>
                    <ul className="list-disc list-inside">
                        <li>
                            xyzABCAIdio
                        </li>
                        <li>
                            ABCakwfbkwaj
                        </li>
                        <li>
                            235jjkndf8
                        </li>
                        <li>
                            mhawd7awfAJKWD
                        </li>
                    </ul>

                    <Button type="submit">Create New Invite</Button>
                </div>
            </div>
        </div>
    );
}
